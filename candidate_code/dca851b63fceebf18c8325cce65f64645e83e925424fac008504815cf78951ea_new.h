// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77950172;
  double density_weight = 0.23325918;
  double prefix_weight = 0.02159900;
  double neighborhood_weight = 0.38660535;
  double late_weight = 0.08551897;
  double critical_weight = 0.10969881;
  unsigned budget = 22;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
