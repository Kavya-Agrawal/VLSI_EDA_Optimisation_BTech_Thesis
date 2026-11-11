// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98317863;
  double density_weight = 0.40573512;
  double prefix_weight = 0.37029135;
  double neighborhood_weight = 0.12340106;
  double late_weight = 0.11657851;
  double critical_weight = 0.14862544;
  unsigned budget = 34;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
