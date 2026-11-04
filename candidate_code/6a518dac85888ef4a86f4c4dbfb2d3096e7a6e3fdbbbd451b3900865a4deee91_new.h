// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.28417448;
  double density_weight = 0.23853631;
  double prefix_weight = 0.22195958;
  double neighborhood_weight = 0.38305718;
  double late_weight = 0.21795486;
  double critical_weight = 0.36195037;
  unsigned budget = 26;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
