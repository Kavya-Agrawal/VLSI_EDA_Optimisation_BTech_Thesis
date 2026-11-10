// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38800583;
  double density_weight = 0.10224269;
  double prefix_weight = 0.45287571;
  double neighborhood_weight = 0.22285827;
  double late_weight = 0.10971929;
  double critical_weight = 0.04933042;
  unsigned budget = 20;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
